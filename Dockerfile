FROM gcr.io/bazel-public/bazel:latest

# 1 - make directory to run container (directory on container)
RUN mkdir /app

# 2 - copy project into newly created directory
COPY . /app

# 3 - CD into new directory for running container
WORKDIR /app

# 4 - compile code
RUN bazel build

# 5 - expose port
EXPOSE 8080

# 6 - run command in docker container once image ran
CMD ["bazel", "run", "//apps/transit_service"]
