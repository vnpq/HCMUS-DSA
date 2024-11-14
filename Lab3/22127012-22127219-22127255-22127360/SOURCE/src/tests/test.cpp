#include "test.h"
#include "../../include/BubbleSort.h"
#include "../../include/RadixSort.h"
#include "../../include/SortContext.h"
#include "../utils/DataGenerator.h"

TEST_CASE("random data") {
  int n = 50000;
  int* a = new int[n];
  GenerateRandomData(a, n);
  BubbleSort bs(a, n);
  SortContext sc(&bs);
  sc.sort();
  std::setprecision(5);
  std::cout << bs.getDuration() << std::fixed << '\n';
  CHECK(std::is_sorted(bs.getArray(), bs.getArray() + n) == 1);
}