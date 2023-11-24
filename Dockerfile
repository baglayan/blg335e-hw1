FROM ubuntu:bionic

RUN apt update
RUN apt install openssh-server sudo -y
RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1000 test 
RUN usermod -aG sudo test
RUN service ssh start
RUN  echo 'test:test' | chpasswd

RUN apt update
RUN apt install build-essential -y
RUN apt install gdb -y

RUN apt update
RUN apt install valgrind

RUN apt update
RUN apt install git -y

RUN apt update
RUN apt install python3 -y
RUN apt install python3-pip -y
RUN sudo update-alternatives --install /usr/bin/pip pip /usr/bin/pip3 1
RUN pip install calico

EXPOSE 22
CMD ["/usr/sbin/sshd","-D"]

COPY QuickSort.cpp /home/ubuntu/hostVolume/hw1/
COPY population1.csv /home/ubuntu/hostVolume/hw1/
COPY population2.csv /home/ubuntu/hostVolume/hw1/
COPY population3.csv /home/ubuntu/hostVolume/hw1/
COPY population4.csv /home/ubuntu/hostVolume/hw1/