import matplotlib.pyplot as plt

# =================================

LARGE = 1000 * 60

# =================================

input_size = [4000, 16000, 32000, 1000000]

case1_IS = [4, 72.989, 290.956, LARGE]
case1_MS = [2, 5.999, 11.998, 323.952]
case1_QS = [0, 3, 4.999, 202.97]
case1_HS = [1, 3, 4.999, 241.963]

case2_IS = [0, 0, 0, 2.999]
case2_MS = [1, 4, 8.999, 240.963]
case2_QS = [5.999, 162.975, 592.91, LARGE]
case2_HS = [0, 2, 5, 164.978]

case3_IS = [9.999, 144.978, 586.911, LARGE]
case3_MS = [1, 4, 7.999, 246.962]
case3_QS = [5.999, 164.975, 527.919, LARGE]
case3_HS = [1, 2, 3.999, 107.984]

# ==================================

plt.figure()
plt.title("case1")
plt.plot(input_size, case1_IS, label = "Insertion Sort")
plt.plot(input_size, case1_MS, label = "Merge Sort")
plt.plot(input_size, case1_QS, label = "Quick Sort")
plt.plot(input_size, case1_HS, label = "Heap Sort")
plt.xlabel("Input Size")
plt.ylabel("Time(ms)")
plt.xscale("symlog")
plt.yscale("symlog")
plt.legend()
plt.savefig("case1.png")
plt.close()

plt.figure()
plt.title("case2")
plt.plot(input_size, case2_IS, label = "Insertion Sort")
plt.plot(input_size, case2_MS, label = "Merge Sort")
plt.plot(input_size, case2_QS, label = "Quick Sort")
plt.plot(input_size, case2_HS, label = "Heap Sort")
plt.xlabel("Input Size")
plt.ylabel("Time(ms)")
plt.xscale("symlog")
plt.yscale("symlog")
plt.legend()
plt.savefig("case2.png")
plt.close()

plt.figure()
plt.title("case3")
plt.plot(input_size, case3_IS, label = "Insertion Sort")
plt.plot(input_size, case3_MS, label = "Merge Sort")
plt.plot(input_size, case3_QS, label = "Quick Sort")
plt.plot(input_size, case3_HS, label = "Heap Sort")
plt.xlabel("Input Size")
plt.ylabel("Time(ms)")
plt.xscale("symlog")
plt.yscale("symlog")
plt.legend()
plt.savefig("case3.png")
plt.close()
