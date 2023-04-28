# Dev guide

This document covers:

1. How to setup the drone simulation on your machine
2. Getting started making changes to the drone simulation
3. How to build+run the drone simulation locally

## Setup on personal computers

to get started, you should clone this repo to your computer:
```bash
git clone https://github.com/leonitousconforti/drone_simulation.git
```

### Windows dependencies

There are three dependencies that you need to install on windows - git, visual studio c++ tools, and bazel. Git is required not only for clone the repo, but we will also use git bash for a bash shell instead of cmd. When installing visual studio 2019 or 2022 community edition, the only thing that needs to be selected in the installer is the c++ tools. These are needed for any c++ development on windows. Finally bazel is needed for our build system. You should install bazelisk from [https://bazel.build/install](https://bazel.build/install)

### Mac dependencies

install bazelisk from homebrew or [https://bazel.build/install](https://bazel.build/install)

### Linux dependencies

install bazelisk from apt or [https://bazel.build/install](https://bazel.build/install)

## Setup for CSE lab machines

The setup for running on CSE lab machines is very similar to running on personal machines, with the one difference being that you do not have admin privileges and bazel is not currently installed on any of them. Not to fear, we can easily work around this.

### CSE linux machines

same dependencies as stated above in the linux section. When downloading bazelisk, just place it in the root of the project and be sure to chmod +x it, then anytime there is a command that start with

```bash
bazelisk ...
```

just replace it with

```bash
./bazelisk ...
```

## Building anywhere

To build all packages in the monorepo

```bash
bazelisk build ...
```

the ... tells bazelisk to build all packages, but if you just want to build a single package you can do that with


```bash
bazelisk build //libs/geometry
```

where //libs/geometry is the package identifier. _Note: it will probably take a minute or two to build the first time, this is because bazel is downloading a couple other dependencies and building them on your computer. Subsequent builds should be much much faster because bazel is really good about caching things_

## Running anywhere

When developing locally, you can run

```bash
bazelisk run //apps/simulation_visualizer
```

to start the simulation on your local machine
