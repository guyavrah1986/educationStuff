# Get the base OS layer. Some best practices notes:
# 1. It is good practice to start from the smallest possible official base image.
# 2. It is good practice to use a specific tag for the base image (and simply "lsatest").
FROM alpine:3.16

# This instructio adds a metadata to the image.
LABEL maintainer="guyavrah1986@gmail.com"

ARG PORT=80

# This insruction adds a layer to the image.
RUN apk add --update nginx

EXPOSE $PORT

CMD ["nginx", "-g", "daemon off;"]