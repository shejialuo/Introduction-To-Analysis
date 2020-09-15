#### 4.1 The maximum-subarray problem

##### 4.1.1 The introduction to the question

Suppose that you been offered the opportunity to invest in the Volatile Chemical Corporation. You are allowed to buy one unit of stock only one time and then sell it at a later date, buying and selling after the close of trading for the day. And <font color="blue">you are allowed to learn what the price of the stock will be in the future</font>.

<font color="red">Your goal is to maximize your profit</font>.

<font color="blue">You might think that you can always maximize profit by either buying at the lowest price or selling at the highest price, however, it is wrong.</font>
##### 4.1.2 A brute-force solution

We can easily devise a brute-force solution to this problem: <font color="blue">just try every possible pair of buy and sell dates in which the buy date precedes the sell date</font>.

A period of $n$ days has $C_{n}^2$ such pairs of dates. Since $C^2_{n}$ is $\Theta(n^2)$, and the best we can hope for is to evaluate each pair of dates in constant time, this approach would take $\Omega(n^2)$

We need to do better.

##### 4.1.3 A transformation

Instead of looking at the daily price, let us instead consider the daily change in price, where the change on day $i$ is the difference between the prices after day $i-1$ and after day $i$. 

<font color="red">We now want to find the nonempty, contiguous subarray of $A$ whose values have the largest sum</font>.We call this contiguous subarray the <font color="blue">maximum subarray</font>.
##### 4.1.4 A solution using divide-and-conquer

Suppose we want to find a maximum subarray of the subarray $A[low \dots high]$. Divide-and-conquer suggests that we divide the subarray into two subarrays of <font color="red">as equal size as possible</font>. That is, we find the midpoint, say `mid`, of the subarray.

Then, we consider the subarrays $A[low \dots mid]$ and $A[mid+1 \dots high]$. <font color="blue">Any contiguous subarray $A[i \dots j]$ of $A[low \dots high]$ must lie in exactly one of the following plcaes</font>. 

+ entirely in the subarray $A[low \dots mid]$, so that $low \leq i \leq j \leq mid$
+ entirely in the subarray $A[mid+1 \dots high]$, so that $mid < i \leq j \leq high$
+ crossing the midpoint, so that $low \leq i \leq mid < j \leq high$

In fact, a maximum subarray of $A[low \dots high]$ must have the greatest sum over all subarrays entirely in $A[low \dots mid]$, entirely in $A[mid+1 \dots high]$ or crossing the midpoint. <font color="blue">We can find maximum subarrays of $A[low \dots mid]$ and $A[mid+1 \dots high]$ **recursively**</font>.

<font color="blue">Any subarray crossing the midpoint is itself made of two subarrays $A[i \dots mid]$ and $A[mid+1 \dots j]$</font>. Therefore, we just need to find maximum subarrays of $A[i \dots mid]$ and $A[mid+1 \dots j]$ and then **combine** them.

The procedure `FIND-MAX-CROSSING-SUBARRAY` does this thing.

```pseudocode
FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
	left-sum = -INF
	sum = 0
	for i = mid downto low
		sum = sum + A[i]
		if sum > left-sum
			left-sum = sum
			max-left = i
	right-sum = -INF
	sum = 0
	for j = mid+1 to high
		sum = sum + A[j]
		if sum > right-sum
			right-sum = sum
			max-right = j
	return (max-left,max-right,left-sum+right-sum)
```

With a linear-time `FIND-MAX-CROSSING-SUBARRAY` procedure in hand, we can write pseudocdoe for a divide-and-conquer algorithm to solve the maximum-subarray problem:

```pseudocode
FIND-MAXIMUM-SUBARRAY(A,low,high)
	if high == low
		return(low,high,A[low]) //base case: only one element
	else 
		mid = ⌊(low + high)/2⌋
		(left-low,left-high,left-sum) = FIND-MAXIMUM-SUBARRAY(A,low,mid)
		(right-low,right-high,right-sum) = FIND-MAXIMUM-SUBARRAY(A,mid+1,high)
		(cross-low,cross-high,cross-sum) = FIND-MAX-CROSSING-SUBARRAY(A,low,mid,high)
		if left-sum >= right-sum and left-sum >= cross-sum
			return(left-low,left-high,left-sum)
		elseif right-sum >= left-sum and right-sum >= cross-sum
			return(right-low,right-high,right-sum)
		else 
			return(cross-low,cross-high,cross-sum)
```

##### 4.1.5 Analyzing the divide-and-conquer algorithm

Next we set up a recurrence that describes the running time of the recursive `FIND-MAXIMUM-SUBARRAY` procedure. We make the simplifying assumption that the original problem size is a power of 2.

We denote by $T(n)$ the running time of `FIND-MAXIMUM-SUBARRAY` on a subarray of $n$ elements. The base case, when $n=1$, is easy:
$$
T(1)=\Theta(1)
$$
The recursive occurs when $n>1$. Each of the subproblems solved is on a subarray of $n/2$ elements, and so we will spend $T(n/2)$ time solving each of them. Because we have to solve two subproblems:

+ <font color="blue">For the left subarray</font>
+ <font color="red">For the right subarray</font>

So we need $2T(n/2)$. As we have already seen, the call to `FIND-MAX-CROSSING-SUBARRAY` takes $\Theta(n)$ time. So we can get the result:
$$
T(n) = \begin{cases}
\Theta(1) &\mbox{if} \ n=1\\
2T(n/2)+ \Theta(n) \ &\mbox{if} \  n>1
\end{cases}
$$
As we shall see from the master method in Section 4.5, this reference has the solution $T(n)=\Theta(n\lg n)$.
