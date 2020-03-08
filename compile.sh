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
  echo "----  Run Build Luanda"
  mkdir -p $OUTDIR
  cd $OUTDIR
  cmake ..
  make
  ls src
  ls test
  echo "----  Complete Build Luanda"
}

function tests {
  echo "----  Run Test Luanda"
  ls
  cd $OUTDIR
  ctest --output-on-failure
  ls Testing/Temporary/
  cat Testing/Temporary/LastTest.log
  echo "----  Complete Test Luanda"
}

function clean {
  rm -rf $OUTDIR
}

function default {
  build && tests
}

cd $BASEDIR
main $*