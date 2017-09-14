# Organizer

Using markdown code from [cpp-markdown](https://github.com/sevenjay/cpp-markdown) repo

### Main functions:
- Store text/lists
- Store links and collect them to groups
- Store Markdown-formatted text (editor and render)
- Auto save information after editing, hiding to tray and closing main window
- Migration of documents on load (Support for loading old-version docs)
- Sync:
    - Generation of keys for secure network transmissions between client and server

### Detailed info
WIP

#### Migrations
Support for loading old versions of storage file (So, if current version 5 and file version is 2, class will apply migrations 3, 4, 5)

### TODO
- Add markdown syntax highlighting and toolbar

- Add files storage (convert file to base64, and encrypt if needed)

  Maybe as FilesGroup, with possible encryption (each gorup with separate key)

- Add support for compiling from .pro
  
- Sync:
    - WIP: Login/Register on server for synchronization ("end-to-end", more info in 'CtyptInfo' file)
    - Server code will be available in separate repository (Rails 5.1 & MySQL)
    - Other clients (Web frontend and Mobile on React library)
