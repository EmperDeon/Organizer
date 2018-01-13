# Organizer

Using markdown code from [cpp-markdown](https://github.com/sevenjay/cpp-markdown) repo

Organizer is an open source, cross-platform app for keeping documents (text notes, links and files).


#### Main functions:
- Store text/lists
- Store links in named groups
- Store files in encrypted storage

#### Features:
- Auto save information after editing
- Hiding to tray
- Migration of documents on load (Support for loading old-version docs)
- Backups

#### License
Organizer is released under the MIT license. See the LICENSE.TXT file that accompanies this distribution for all the details that only a lawyer could love, but the general idea is that you can do pretty much anything you want with the code except claim that it's your own work.
    

## Detailed info
Each document is separate tab.

### Files
Storage folder:
- Linux: `~/.organizer/`
- Windows: `%HOME/.organizer/`

Structure:
- `storage.json` - Main storage (docs, configs)
- `backup_week.json` - Weekly backup
- `backup_last.json` - Backup for last 3 launches
- `encrypted_files/` - Dir for "FilesGroup" tabs


### Storage
Main file, for storing configs and docs.

Structure:
```
{
 "sync": false

 "docs": [
   {
     "name": <doc name, string>,
     "type": <doc type, int>,
     "last_updated": <last save datetime>,
     "content": <doc data, QJsonValue>,
     "version": <doc version, int>,
   
     // Custom fields
     "files": [
       {
         name: <file_name>,
         hash: <sha256 of file, used for verification>,
         size: <size string>
         type: <name for icon>,
       },...
     ],
     "file_key": <tab_folder_key>
   },...
 ],
 
 "version": <storage version>
}
```


### Migrations
Support for loading old versions of storage file (So, if current version 5 and file version is 2, class will apply migrations 3, 4, 5)


### Backups
Backup is created at storage loading, after migrations are applied

Structure:
```
{
  <Date, formatted as 'ISO86801'>: {
    "docs": "...",
    <Any fields, required for docs loading>
  },...
}
```

#### Weekly Backups
Backup is done at the start of the week (if program is launched in that week).

#### Last backups
Storing docs at last 3 launches


## TODO's
### TODO order
- README
- Markdown toolbar
- Prepare for first release


### Big TODO's
- Prepare for first release
  - Add support for compiling from .pro
  - Check minimal qt version (ex. 5.5, or 5.2)
  - Add qca as vendor subproject
  - Check and add license
  
- README
  - Write requirements and build instructions
  - Screenshots


### Small TODO's
- Add markdown syntax highlighting and toolbar

- Themes [Light, Dark] as default, and custom (JSON)

- Custom groups of tabs

- Options for compression, encryption(yes, return the old deleted system), backups and encryption of whole storage file

- Encryption of storage with local password
  - Remember me, for time set by user


#### Other 
##### Needs further checking
- network/NCrypt:decrypt - Validation error prints only to console and message decryption isn't stopped


##### Maybe
- Move all "secure" variables from storage to separate file or leave there but encrypted like docs (for ex. to SSecure)
- Move login/register logic to SSecure
