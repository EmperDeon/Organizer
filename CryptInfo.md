#### All of this is generally for `sync` git branch

## Storage
All in 1 file: storage.json

Default:
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

Encrypted:
```
{
 "sync": true

 "docs": <AES>,
 
 "last_login": <last login>,
 "remember": true,
 
 "network_inited": true,
 "uid": <generated UID>,
 "net_key": <generated network AES>,
 "rsa_pr": <generated network RSA Private key>,
 "rsa_pu": <generated network RSA Public key>,
 "server_pub": <server RSA Public key>,
 
 "version": <storage version>
}
```


### Documents
- By default `docs` are stored unencrypted
- When sync enabled, `docs` are encrypted with `Documents key`


### Documents key
- Generated on registration (enabling sync)
- Length in `S_DOC_KEY_SIZE` var
- Encrypted with `User credentials` and are stored locally and in sync server DB


### User credentials
- SHA256 hash of `login:password:salt`


## Network
By default (with my server) this is not used, because of strict HTTPS.
But, if you use own server, and don't want to deal with HTTPS, you can enable HTTP mode, and it will use mechanism described below.

### Requests and responses
First request (when no symmetric key is generated) will be encrypted with Public RSA server key.
To ensure that Man-In-The-Middle can't access or modify data, you will need to copy Public RSA server key to field in the settings. 
All parameters are encrypted with AES-128 and signed with RSA

### On first request
- Enter `User credentials`
- Generate UID (Used as Client identifier)
- Generate AES-128 key (Used as key for params encryption)
- Generate RSA 2048, passphrase - hash (Used for params verification)
- Send POST to `network-init` at server

First requests (`network-init`, `check_inited`) are encrypted with key defined in `NETWORK_DEF_KEY` var

### On register
WIP

### On login
WIP
