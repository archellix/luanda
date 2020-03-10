#!/bin/sh

OUTDIR=_out
DOCSDIR=docs
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
  echo "----  Complete Build Luanda"
}

function tests {
  echo "----  Run Test Luanda"
  cd $OUTDIR
  ctest --output-on-failure
  echo "----  Complete Test Luanda"
}

function docs {
  echo "----  Run Document generation"
  cd $BASEDIR
  doxygen doxyfile
  echo "----  Complete Document generation"
}

function clean {
  rm -rf $OUTDIR
}

function default {
  build && tests
}

function publish {
  docs
  mkdir -p $DOCSDIR
  cp -R $OUTDIR/docs/html/* $DOCSDIR
}

cd $BASEDIR
main $*