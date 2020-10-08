FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc p1.c -o p1
RUN chmod +x p1