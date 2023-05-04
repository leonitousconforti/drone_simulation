# Drone Simulation

[![Bazel Build](https://github.com/leonitousconforti/drone_simulation/actions/workflows/bazel_build.yml/badge.svg?branch=main)](https://github.com/leonitousconforti/drone_simulation/actions/workflows/bazel_build.yml)

__see the [README_Project.md](./README_Project.md) for the documentation about the project, here's what changed though__

## The build system

Makefiles work great... if you are on a unix system. But what about all us who use windows? In my opinion, the experience of setting up make support on windows leaves a lot to be desired. Even if you managed to setup make on windows, this repo used to only ship with linux dependencies, so good luck trying to find the source code for all the deps and especially good luck trying to compile them all for windows! But leo, "Just use WSL!" I hear you say. Well, I have a macbook air, so while I could use WSL on my desktop at home, I spend an equal amount of time developing on my laptop where WSL is not an option. What about setting up a linux devcontainer using docker on my macbook and Windows pc? That way I can develop in a linux environment no matter where I am (I love devcontainers btw, you can see I also use them for this repo). Well, once again, this repo used to only ship linux X86_64 deps, so even if I got a linux devcontainer setup on my m1 macbook, I can't compile it because they are the wrong architecture (rosetta lets you run x86_64 apps on m1 macs, but I couldn't find any way to cross compile x86_64 deps to still target x86_64 using gcc on an m1 mac, maybe I am missing something but I also needed to do that in a devcontainer so that it was on linux and docker+rosetta is still in beta).

I really wanted to improve the DX (developer experience) of working on this project. Specifically, my goals were to:

1. Make this project cross platform and architecture independent. Not only do I want to be able to compile this project for all platform and be able to run it anywhere but I also wanted to be able to develop this project anywhere. I know that docker would allow me to run this anywhere, but as someone who develops on their m1 macbook laptop throughout the day, their windows machine at home, and the cse lab machines when they absolutely have to it sucks have to be tied to the cse lab machines for this project. Even though remoting in and setting up port forwarding are very well documented, every time my computer falls asleep or I close the lid I have to re authenticate, which just makes it feel like a chore. If that was my only problem, I would not have changed the entire build system, but my other more painful gripe is intellisense.

2. Improve the intellisense support, as it just wouldn't work for me on some things. I wouldn't consider myself a pick and choose developer who just scrolls through intellisense until they find find something that looks right, but I do appreciate it when I can quickly and automatically import all the files I need and when I can hover for documentation.

3. Improve the project structure. I felt like there were quite a few redundant and unnecessary parts of the project that increased complexity and coupling for no reason, which made it more difficult to understand at first. As an example, all routing strategies used to be paired to a graph, such that if you gave a graph to a routing strategy it would calculate the path from point A to B. But all graphs used to also be paired to routing strategies, such that if you gave a routing strategy to a graph it would calculate the path from point A to B. This creates a cyclic dependency loop, graphs depend on routing strategies and routing strategies depend on graphs. It just makes things harder to read to because of the syntax and mental work that goes in to overcoming this. So I ask, why do they both need to be coupled to each other? If anyone has a good response as to why it needs to be that way, then yeah it can be that way. But in my mind, I'm not here to philosophize about whose responsibility it is to calculate paths, I just said that only routing strategies will ever need to calculate paths in our system - and it works just fine. Likewise, why does there need to be three different definitions for a Vector3 class when they all pretty much boil down to the same thing? Also having header and source folders increases the number of files shown to the developer at a time, which also increases the cognitive load needed by the developer. So I propose that all files related to one another go in the same folder, and that files are separated based on the domain/responsibility. This is also how most of Google's monorepos are structured and I find it helps me a lot.

I determined that the best way to accomplish these goals was through a different build system. I ultimately decided to use either CMake or Bazel. While I have had some experience using CMake, I had no prior experience using bazel before this project. So why did I decide to go with bazel?

1. Its the build system that Google uses. As stated in the syllabus under "why c++", we use c++ because it is the language that big tech companies use to develop really big software programs. For a class that is all about developing really big software programs in teams, why don't we also use a build system that is designed for that and supports that? I don't think that Make is a bad build system, nor do I think it was the wrong choice for this project, but I do believe that better tooling enables developers to write better software and it feels like we are stuck in the 1990's almost.

2. Multi language support. The web aspect of this project was written in Javascript + html + css, and when I was doing research about CMake and bazel, one of the things that stood out to me was bazel's multi language support. You no longer needed to have two different build systems for different languages, they could all be unified with bazel and you could share code across languages in really cool ways. One of the ideas I explored was using protobufs for the web to simulation communication so I could still get strictly typed values in the javascript (which I think would improve the DX quite a bit) and would eliminate the need for JSON in the c++.

3. Cross platform / architecture independent. I wanted to make this project cross platform and architecture independent, so having a build system that supported that was going to make my life easier.

4. Its engineered for big projects, not that CMake is not, but bazel is designed for monorepos first

## Project structure

The project is now split into 6 independent packages - 4 of which are libraries and 2 of which are apps. The factor on what is a lib vs what is an app comes down to one question: Does it produce an executable? If it does produce an executable that you can run, then it is an app. But if all it produces is a shared/static library, then it is a lib.

### Building libs

Libraries are very simple to build, for example:
```bash
bazelisk build //libs/routing
```

### Running apps

You can build apps the same way that libs are built, which is great if you just want to check that it will compile. But if you want to run it, all you need to do is:
```bash
bazelisk run //apps/simulation_visualizer
```

## Native vs Web

In my quest to make this project cross platform and architecture independent, I wanted to get rid of as many third party dependencies as possibly. I noticed that the web aspect, i.e the web server and the websockets, were responsible for a majority of the dependencies. And no matter how hard I tried, building libwebsockets and the required dependencies on all platforms proved quite the challenge. And if I couldn't build libwebsockets on all platforms using bazel, then I would have to use a different c++ webserver library for the web component. And that would mean rewriting the entire c++ web component. I was up for that, as that would give me a chance to rewrite the frontend using typescript and I was already theorizing about if I could use protobufs to get end-to-end type checking and eliminate JSON. But what if we could do even better than that? If we need some kind of c++ frontend to interact with the simulation c++ code, why not have it be a native application? Then we could keep the entire codebase as c++ and eliminate all the JS/html/css and the webserver dependencies. Also, think about the framerate boost we could achieve using a native application and maybe even some GPU rendering! I tried QT at first because that is what I read online is a really good cross platform c++ GUI framework. But I quickly realized no one had it working with bazel (you have to use custom build tools) and it didn't have any of the 3d rendering utilities I would need builtin. After quite a bit of digging and research, I landed on RayLib (never heard of it before this), a mini c++ game dev framework which satisfied all my requirements of being cross platform, 3D rendering out of the box, and quite a bit of documentation and examples to learn from.

## Simulation Api

Now that I had decided to go with a native application, I wanted to change the simulation package's API. I thought about how I would want to interact with the simulation from the native application, and this is what I cam up with. Its a little convoluted around the getEntityBuilder part, but I feel it hits on most of the big design patterns we talked about in class

```c++
int main(void) {
  // We use the singleton pattern to only allow one instance of the
  // SimulationModel at a time.
  SimulationModel* sm = SimulationModel::getInstance();

  // We use the builder pattern to construct entities.
  DroneBuilder* droneBuilder = new DroneBuilder();
  Drone* drone = droneBuilder->addPosition({0, 0, 0})
                     ->addSpeed(1.0f)
                     ->addAvailability(true)
                     ->construct();

  // We use the decorator pattern to add unique functionality to the drone
  Drone* droneWithBat = new BatteryDecorator(drone);

  // Add the drone to the sim
  sm->addEntity(droneWithBat);

  // And schedule a trip from the RecWel to Carlson school of Business
  sm->scheduleTrip("My first trip!", {0, 0, 0}, {1, 1, 1});

  // ...
  sm->update(1.0f);

  // Don't forget to cleanup (since we didn't use a smart pointer)
  delete sm;
  return 0;
}
```

## Final result

Build artifacts can be found from the most recent successfully CI/CD run. The artifact name includes the platform they were _built on_, however, bazel targets windows10 macos12 and ubuntu20.04. That means the windows11 binaries will still run on windows10 they just happened to be built on windows11. In short, you can download either one of the downloads for your platform. You will need to chmod the executable on linux and macos, and windows defender will probably tell you that it is from an unknown publisher - if you are really worried, you can read the source code or build it yourself. And you shouldn't change the directory structure of the artifacts, for example, the simulation_visualizer executable and simulation_visualizer.runfiles folder must be next to each other! So if you copy the executable to your desktop or somewhere else, don't forget to copy the .runfiles folder there to, they are required.

Also this really doesn't need to be a million lines of code (or whatever the number was said to be at the beginning of the semester), it only needs less than 5000 SLOC.
