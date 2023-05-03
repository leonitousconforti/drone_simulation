# https://bazel.build/install/docker-container
FROM gcr.io/bazel-public/bazel:latest

# 1 - make directory to run container (directory on container)
USER root
RUN mkdir /app

# 2 - copy project into newly created directory
COPY --chown=bazel . /app

# 3 - CD into new directory for running container
WORKDIR /app

# 4 - compile all projects in the monorepo
RUN bazel build //libs/simulation:example

# 5 - run command in docker container once image ran
CMD ["bazel", "run", "//libs/simulation:example"]
