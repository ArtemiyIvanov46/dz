import numpy as np
def linsys(n, m, matrix):
  k = matrix[:, :m-1]
  v = matrix[:, m-1:]

  try:
    x = np.linalg.solve(k, v)
    return x.flatten().tolist()
  except np.linalg.LinAlgError:
    return None

n, m = map(int, input().split())
matrix = []
for _ in range(n):
    r = list(map(float, input().split()))
    matrix.append(r)
matrix = np.array(matrix)
solution = linsys(n, m, matrix)
if solution is not None:
    print("Решение:")
    i = 1
    for  x in (solution):
        print(f"x{i} = {x}")
        i += 1
else:
    print("Система не имеет решения или имеет бесконечно много решений.")