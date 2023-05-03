#!/bin/bash

IMG="https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/e4d746c4-b5bc-4d8f-8aff-ffcdf9f1a54e/df3vrem-80897ba0-6796-45d0-9145-f132c9ff5ba7.png?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7InBhdGgiOiJcL2ZcL2U0ZDc0NmM0LWI1YmMtNGQ4Zi04YWZmLWZmY2RmOWYxYTU0ZVwvZGYzdnJlbS04MDg5N2JhMC02Nzk2LTQ1ZDAtOTE0NS1mMTMyYzlmZjViYTcucG5nIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmZpbGUuZG93bmxvYWQiXX0.QLq0lO9Y-OEnZ7XBT_mk55SDw7KnzL9mWAcT2FJ09sw"
URL="https://api.telegram.org/bot5364530727:AAFgke_tFxdul0bmIZwXqCKjHCjTXo1HGrQ/sendPhoto"
TEXT="Student: cmerlyn
Status $1: $2
Project: $CI_PROJECT_NAME
URL: $CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID
Branch: $CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=1087679756&photo=$IMG&caption=$TEXT" $URL > /dev/null