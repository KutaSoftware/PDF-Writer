FROM python:3.6 AS build

ARG NEXUS_CREDENTIALS

WORKDIR /pip-packages/
RUN pip download --index-url https://${NEXUS_CREDENTIALS}@intranet.gradiant.org/nexus/repository/pypi-biometrics/simple --extra-index-url https://pypi.python.org/simple --trusted-host intranet.gradiant.org gradiant-bowie


FROM ubuntu:18.04
LABEL maintainer="Valida Support <valida.support@gradiant.org>"

COPY --from=build /pip-packages/ /pip-packages/
RUN apt-get update && \
    apt-get install -y zip build-essential cmake gcc git curl

RUN apt-get install -y software-properties-common && \
    add-apt-repository ppa:deadsnakes/ppa && \
    apt-get update && \
    apt-get -y install python3.6 python3.6-dev python3.6-distutils&& \
    apt-get autoremove

RUN curl https://bootstrap.pypa.io/get-pip.py | python3.6
RUN rm -f /usr/bin/python && ln -s /usr/bin/python3.6 /usr/bin/python
COPY --from=build /pip-packages/ /pip-packages/
RUN python3.6 -m pip install --no-index --find-links=/pip-packages/ /pip-packages/* && rm -rf /pip-packages

COPY docker_files/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
CMD /entrypoint.sh

