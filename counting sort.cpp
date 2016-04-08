计数排序，顾名思义，就是对待排序数组按元素进行计数。使用前提是需要先知道待排序数组的元素范围，将这些一定范围的元素置于新数组中，新数组的大小为待排序数组中最 大元素与最小元素的差值。

维基上总结的四个步骤如下：

定新数组大小——找出待排序的数组中最大和最小的元素
统计次数——统计数组中每个值为i的元素出现的次数，存入新数组C的第i项
对统计次数逐个累加——对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
反向填充目标数组——将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1
其中反向填充主要是为了避免重复元素落入新数组的同一索引处。