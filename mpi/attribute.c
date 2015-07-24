#include <stdio.h>
#include <mpi.h>


/*
 * MPIの属性処理関数のテスト
 * getAttribute
 *   属性MPI_WTIME_IS_GLOBALの値を読み出力する関数
 * setAttribute
 *   そのうち実装
 */

void getAttribute();


int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  getAttribute();

  MPI_Finalize();
  return 0;
}


void getAttribute() {
  void *v;
  int vval;
  int flag;

  MPI_Attr_get(MPI_COMM_WORLD, MPI_WTIME_IS_GLOBAL, &v, &flag);
  if (flag) {
    vval = *(int*)v;
    printf("Value of \"MPI_WTIME_IS_GLOBAL\" is %d\n", vval);
  } else {
    printf("Error: cannot read the value of \"MPI_WTIME_IS_GLOBAL\"\n");
  }
}
