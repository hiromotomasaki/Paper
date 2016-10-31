#!/bin/bash

# *.orgと*.texファイル以外を削除する
ls | grep -v -E '*.tex$|*.org$|*.sh$|*.sty$|*.bst$|Graphics' | xargs rm -r
