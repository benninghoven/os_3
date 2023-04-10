# Use an official Ubuntu 20.04 LTS as a parent image
FROM ubuntu:20.04

# Install necessary packages and dependencies
RUN apt-get update && apt-get install -y gcc git

WORKDIR /app

COPY . .



# Set the default command to run when the container starts
CMD ["bash"]

