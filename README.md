# PDFWriter

This repository contains Gradiant´s version of PDFWriter library. Versions of this library are stored in [Nexus](https://repo.gradiant.org/nexus/#browse/browse:raw-dataset-biometrics:pdfwriter).

## Requirements
* gradiant-bowie==0.7.1

## Build
~~~
bowie -b
~~~

## Generate new version for Nexus and upload it

### Build the docker image
You can skip this step if you already have it.
You must define the environment variable 'NEXUS_CREDENTIALS=ldap_user:ldap_password'. Then:

~~~
docker build -t pdfwriter -f docker/Dockerfile --build-arg NEXUS_CREDENTIALS=$NEXUS_CREDENTIALS .
~~~

### Tag you commit
Assign a new version tag  (with format "vX.Y.Z") to the current commit
~~~
git tag vX.Y.Z
~~~

### Run the container
You must define the environment variable 'NEXUS_CREDENTIALS=ldap_user:ldap_password'. Then:
~~~
 docker run -e NEXUS_CREDENTIALS=$NEXUS_CREDENTIALS -v $PWD:/pdfwriter -it pdfwriter
~~~
The new version should be uploaded to Nexus.
## Build for local use
### With bowie
~~~
bowie -b
~~~
### With cmake
~~~
mkdir build
cd build
cmake ..
make -j4
~~~

## Build as dependency

It is possible to dissable the building of the tests of this project. This is useful if a target with the same name (unit_test) exists in the parent project, to avoid error due to duplicated targets.
To do this the "AVOID_PDFWRITER_TESTS" variable should be set before include this project.