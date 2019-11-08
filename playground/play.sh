#!/usr/bin/env bash

set -e;

OLD_PWD=$(pwd);
EXAMPLE=$1;
VERSIONS=("a" "b" "c" "d" "e" "f");

if [ -z $EXAMPLE ]; then
    EXAMPLES=$(find playground -mindepth 1 -maxdepth 1 -type d -exec basename {} \;);
else
    EXAMPLES=("$EXAMPLE");
fi;

for EXAMPLE in ${EXAMPLES[@]}; do
    echo "Playing with $EXAMPLE";

    for VERSION in ${VERSIONS[*]}; do
        DIR="$OLD_PWD/playground/$EXAMPLE/$VERSION";

        if [[ -d "$DIR" ]]; then
            cd "$DIR";
            [[ -d "./node_modules" ]] || npm ci;
            npm run build;
        fi;
    done;
done;

cd "$OLD_PWD";

set +e;