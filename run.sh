docker build -t localhost/combots . && \
docker run --rm -it \
      -v $PWD/src:/tmp/src \
      -v $PWD/launch:/tmp/launch \
      --network=host \
      localhost/combots \
      bash
