/*
	The MIT License

    Copyright (c) 2009 by Chad Nelson

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef MARKDOWN_H_INCLUDED
#define MARKDOWN_H_INCLUDED

#include <iostream>
#include <string>
#include <list>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/unordered_map.hpp>

namespace markdown {

    using boost::optional;
    using boost::none;

    // Forward references.
    class Token;

    class LinkIds;

    typedef boost::shared_ptr<Token> TokenPtr;
    typedef std::list<TokenPtr> TokenGroup;

    class Document {
    public:
        explicit Document(size_t spacesPerTab = cDefaultSpacesPerTab);

        explicit Document(std::istream &in, size_t spacesPerTab = cDefaultSpacesPerTab);

        ~Document();

        // You can call read() functions multiple times before writing if
        // desirable. Once the document has been processed for writing, it can't
        // accept any more input.
        bool read(const std::string &);

        bool read(std::istream &);

        void write(std::ostream &);

        void writeTokens(std::ostream &); // For debugging

        // The class is marked noncopyable because it uses reference-counted
        // links to things that get changed during processing. If you want to
        // copy it, use the `copy` function to explicitly say that.
        //Document copy() const; // TODO: Copy function not yet written.

    private:

        bool _getline(std::istream &in, std::string &line);

        void _process();

        void _mergeMultilineHtmlTags();

        void _processInlineHtmlAndReferences();

        void _processBlocksItems(TokenPtr inTokenContainer);

        void _processParagraphLines(TokenPtr inTokenContainer);


        static const size_t cSpacesPerInitialTab, cDefaultSpacesPerTab;

        const size_t cSpacesPerTab;
        TokenPtr mTokenContainer;
        LinkIds *mIdTable;
        bool mProcessed;
    };

    std::string md2html(std::string in);

} // namespace markdown

#endif // MARKDOWN_H_INCLUDED
