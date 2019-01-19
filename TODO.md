### Projects

- Prepare for first release
  
- README
  - Screenshots


### Broken

- WTSorter - no support for uuids
- FilesGroup - encryption and decryption
- New tab isn't added to current group
- `cpp-markdown` doesn't compile with gcc7


### Current roadmap

- Move sensitive variables to SSecure (with static key for now)

- Fix markdown crash on tab character - debug and create pull-request
  - Crash after creating submenu
  ```
  - First row
    - <Crash here>
  ```


- Rename `doc` to `note` in README

- Logging
  - Add logging to already written code for debug/bug hunting.
  - Implement QDebug-like interface (at least for int, string and json)

- Fix bugs:
  - Crash on first(empty) start
  - Windows blinks multiple times on start
    - Multiple (10-12) saves after app starts (Maybe it's just auto save after edit ?)
  - Don't work correctly with dock (`plank`) until hidden to tray and shown back
    - Bug present only if desktop entry is created (misconfiguration ?)
  - Keyboard language don't change (Dev bug?)


### Low priority roadmap
  
- Welcome screen with quick links to groups/last edited tabs/settings

- Logging
  - Load logging settings from storage with silent flag

- Compress Journal's content

- Modals (settings) as pinned first tab, closed on save/cancel

- Logs widget [WIP in branch `logs_widget`]
  - Archiving old logs (store unzipped 2-3 files, rest is in logs.zip)
  - Send logs with button (dunno, host an app for it ?)
  - Check `Q_FUNC_INFO` on other compilers/platforms
    - Works correctly on `GCC Ubuntu 5.4.0`

- Double-Shift or some other shortcut to quickly go to any tab | switch options

- Encryption of storage with local password
  
- Add UUIDs to tabs, move groups out to separate key
  - Change Journal to UUID, sort order & date in doc
  - Add universal widget for sorting SMap elements

- Import/Export through menu item
  
- Write docs in code

- Restore and Diff for Backup [Move to sync ?]

- View-only mode for LinkGroup

- Add markdown syntax highlighting and toolbar
  - Custom markdown render to QLabel, etc as module (push to GitHub as separate rep)

- Themes [Light, Dark] as default, and custom (JSON or QSS)


#### Other 
##### Needs further checking
- network/NCrypt:decrypt - Validation error prints only to console and message decryption isn't stopped
  - Show QMessageBox with question about trust


##### Maybe
- Rewrite to Model-View, to cleanup code and use less code
- Move login/register logic to SSecure
- Sync:
  - TOTP [repo 1](https://github.com/RavuAlHemio/cpptotp), [repo 2](https://github.com/andreagrandi/QGoogleAuth)
  - Docs sharing - (one time, continuous, two way, exchange keys with RSA)
