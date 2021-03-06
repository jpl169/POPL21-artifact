##################################################################
# Docker Build Variables. Please set them before build docker image
##################################################################
ARG soplex401TarFile=/Users/jay/Research/soplex-4.0.1.tar


##################################################################

FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

##################################################################
# Install necessary apt packages
##################################################################
RUN apt-get update && \
    apt-get install -yq --no-install-recommends apt-utils && \
    apt-get install -yq build-essential \
    	    	        cmake \
    	    	    	git \
			libgmp3-dev \
			libmpfr-dev \
			zlib1g \
			zlib1g-dev \
			bc \
			wget \
			python \
			python3 \
			python3-pip \
			emacs && \
    pip3 install --upgrade pip && \
    python3 -m pip install matplotlib

WORKDIR /home

####################################################################
# Move soplex 4.0.1 and build it
####################################################################
COPY soplex-4.0.1.tar /home/soplex.tar
RUN tar -xvf soplex.tar && \
    cd soplex-4.0.1/ && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    cd ../..

ENV SOPLEXPATH=/home/soplex-4.0.1/


####################################################################
# Install SoftPosit
####################################################################
RUN git clone https://gitlab.com/cerlane/SoftPosit.git && \
    cd SoftPosit/build/Linux-x86_64-GCC/ && \
    make && \
    cd ../../..

ENV SOFTPOSITPATH=/home/SoftPosit/

####################################################################
# Install SoftPosit-Math
####################################################################
RUN git clone https://gitlab.com/cerlane/softposit-math.git && \
    cd softposit-math/build/ && \
    ./make.sh && cd ../..

ENV SOFTPOSITMATHPATH=/home/softposit-math

####################################################################
# Git Clone POPL21 artifact
####################################################################
RUN git clone https://github.com/jpl169/POPL21-artifact.git
WORKDIR /home/POPL21-artifact
