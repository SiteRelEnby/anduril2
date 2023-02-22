#! /usr/bin/env bash
# Requires BuildKit: https://docs.docker.com/build/buildkit/
# By default: builds the firmware builder image locally for the local system's arch only.
# To instead build a multiarch image, pass USE_MULTIARCH=1 and DOCKER_REGISTRY="https://docker-registry.example.com". This *should* work with Docker Hub but I haven't tested it. This may or may not work on Windows, but the default build should work fine, and if you only run Windows and still really want a multiarch image (rather you than me...), feel free to test and fix it; it's not something I see any need for personally so can't really be arsed right now.
init_buildx(){
	docker run --privileged --rm tonistiigi/binfmt --install all
	docker run --rm --privileged multiarch/qemu-user-static --reset -p yes
	docker buildx rm builder
	docker buildx create --name builder --driver docker-container --use --driver-opt env.BUILDKIT_STEP_LOG_MAX_SIZE=10485760 #10485760 = 10MiB
	docker buildx inspect --bootstrap
}
set -e
set -o pipefail
cd anduril-buildenv-docker
[[ ! -f Dockerfile ]] && echo 'Dockerfile is missing. Did you run `git submodule update --init` ?' >&2 && exit 1
if [[ "${BUILD_MULTIARCH}" == "1" ]]
then
	[[ -z "${DOCKER_REGISTRY}" ]] && echo "need a docker registry URL" >&2 && exit 1
	if (docker ps | grep builder)
	then
		continue
	else
		init_buildx
	fi
	docker buildx build --platform linux/arm/v7,linux/arm64,linux/amd64 --push --tag ${DOCKER_REGISTRY}:anduril-builder:latest .
	docker pull ${DOCKER_REGISTRY}:anduril-builder:latest
else
	docker build --rm -t anduril-builder:latest .
fi
