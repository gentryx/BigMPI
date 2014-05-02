#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "bigmpi.h"

int MPIX_Send_x(const void *buf, MPI_Count count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    int rc = MPI_SUCCESS;

    if (count <= BIGMPI_MAX_INT ) {
        rc = MPI_Send(buf, (int)count, datatype, dest, tag, comm);
    } else {
        MPI_Datatype newtype;
        MPIX_Type_contiguous_x(count, datatype, &newtype);
        MPI_Type_commit(&newtype);
        rc = MPI_Send(buf, 1, newtype, dest, tag, comm);
        MPI_Type_free(&newtype);
    }
    return rc;
}

int MPIX_Recv_x(void *buf, MPI_Count count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
    int rc = MPI_SUCCESS;

    if (count <= BIGMPI_MAX_INT ) {
        rc = MPI_Recv(buf, (int)count, datatype, source, tag, comm, status);
    } else {
        MPI_Datatype newtype;
        MPIX_Type_contiguous_x(count, datatype, &newtype);
        MPI_Type_commit(&newtype);
        rc = MPI_Recv(buf, 1, newtype, source, tag, comm, status);
        MPI_Type_free(&newtype);
    }
    return rc;
}
