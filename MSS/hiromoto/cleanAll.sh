#!/bin/bash

# ''以外を削除する
ls | grep -v -E '*.sh$|*.cls$|*.1st$|*.tex$|*.bst$|*.pdf$' | xargs rm -r
