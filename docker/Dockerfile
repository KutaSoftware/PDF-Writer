FROM python:3.6 AS build

ARG NEXUS_CREDENTIALS

WORKDIR /pip-packages/
RUN pip download --index-url https://${NEXUS_CREDENTIALS}@intranet.gradiant.org/nexus/repository/pypi-biometrics/simple --extra-index-url https://pypi.python.org/simple --trusted-host intranet.gradiant.org gradiant-bowie


FROM ubuntu:18.04
LABEL maintainer="Valida Support <valida.support@gradiant.org>"

RUN apt-get update && \
    apt-get install -y zip build-essential cmake gcc