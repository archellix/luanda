#!/bin/sh

OUTDIR=_out
DEFAULT_TARGET=default
BASEDIR=$(dirname $0)

function main {
  if [ "$1" == "" ]; then
    TARGET=$DEFAULT_TARGET
  else
    TARGET=$1
  fi
  
  $TARGET
}

function build {
  mkdir -p $OUTDIR
  cd $OUTDIR
  cmake ..
  make
}

function tests {
  cd $OUTDIR
  ctest --output-on-failure
  ls test
  ls _out
  ls _out/test
}

function clean {
  rm -rf $OUTDIR
}

function default {
  build && tests
}

cd $BASEDIR
main $*