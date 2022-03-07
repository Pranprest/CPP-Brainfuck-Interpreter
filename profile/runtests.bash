#!/usr/bin/env bash
make release || exit 
time build/bfi sample/yapi.bf 