
#1
    In this project we use concept of well known address/name for FIFO IPC between
    execution manager(server) and executable applications (clients). As pointed in
    specification the place in which FIFO shall be created is /usr/run/exectuion-manager;
    the name for a FIFO shall be appstate-server-fifo. Run appstate_server_fifo_create.sh
    script (with chmod +x beforehand) with sudo to create this directory with the named
    FIFO within. Program WILL NOT RUN without this step. For that reason we check for the
    existence of the FIFO during the CMake configuration stage.
#2
    For the same reason above, i.e. the usage of /usr directory, main executable(EM_EXEC)
    must be used with sudo. Otherwise it will fail to open the FIFO.
