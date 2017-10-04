# Organizer

Using markdown code from [cpp-markdown](https://github.com/sevenjay/cpp-markdown) repo


### Main functions:
- Store text/lists
- Store links and collect them to groups
- Store Markdown-formatted text (editor and render)
- Auto save information after editing, hiding to tray and closing main window
- Migration of documents on load (Support for loading old-version docs)


### Detailed info
WIP

#### Migrations
Support for loading old versions of storage file (So, if current version 5 and file version is 2, class will apply migrations 3, 4, 5)


### TODO order
- Files
- README
- FIXME's
- Markdown toolbar
- Prepare for first release

##### FIXME
- Delete tab not working
- Moving tabs does not affect storage

##### Big TODO's

- Add files storage (copy to 'encrypted_storage', and encrypt if needed)
  - Maybe as FilesGroup, with possible encryption (each group with separate key)
  - 

- Prepare for first release
  - Add support for compiling from .pro
  - Check minimal qt version (ex. 5.5, or 5.2)
  - Add qca as vendor subproject
  - Check and add license
  
- README
  - Simplify Main functions
  - Write requirements and build instructions
  - Screenshots

##### Small TODO's
- Add markdown syntax highlighting and toolbar

- Themes [Light, Dark] as default, and custom (JSON)

- Custom groups of tabs
    
   
#### Other 
##### Needs further checking
- network/NCrypt:decrypt - Validation error prints only to console and message decryption isn't stopped


##### Maybe
- Move all "secure" variables from storage to separate file or leave there but encrypted like docs (for ex. to SSecure)
- Move login/register logic to SSecure
