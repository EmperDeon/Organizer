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
     "content": <doc data, json>,
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


### Settings
Setting entries are stored in res/settings.json
Values (configured by user) are stored in `Storage.settings`

Types on setting entries:
- boolean: CheckBox
- integer: LineEdit with IntValidator
- string: LineEdit
- select: ComboBox
- list: LineEdit

Example:
```
{
  "name": "storage_encrypt",
  "description": "Encrypt(AES) storage.json on save with predefined key ?",
  "default": false,
  "type": "boolean"
},
{
  "name": "test_option_a",
  "description": "Test 1",
  "default": 123,
  "type": "integer"
},
{
  "name": "test_option_b",
  "description": "Test 2",
  "default": "custom default string",
  "type": "string"
},
{
  "name": "test_option_c",
  "description": "Test 3",
  "default": "val1",
  "type": "select",
  "list": [
    [
      "Option 1",
      "val1"
    ],
    [
      "Option 2",
      "val2"
    ],
    [
      "Option 3",
      "val3"
    ]
  ]
},
{
  "name": "test_option_d",
  "description": "Test 4",
  "default": "1, 2",
  "type": "list"
}
```

### Logs
Logging to console/file.

Levels:
- Error - Unexpected behavior
- Warning - Expected, but unwanted
- Info - Ordinary events, like file loading
- Debug - For developer, for debugging
- Verbose - Hidden by default, used for dumping strings/json, or very frequent events

Example - Hide sensitive data from logs (file names, JSON) :
```
QFile in(f_in);
if (!in.open(QFile::ReadOnly)) {
    logE("Could not open file for read");
    logV(f_in);
    return;
}
```


### Encryption of tabs
Encrypt one document with password.
Affects only `content` field
