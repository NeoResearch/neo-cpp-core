#!/bin/bash

npm install
npm run build
(cd tests && npm install)
nohup npm run serve&
(cd tests && npm test)
pkill http-server #finish server
