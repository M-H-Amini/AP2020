import numpy as np

def fibonacci(n, series=[1, 1]):
    if n > len(series):
        series.append(fibonacci(n - 1, series) + fibonacci(n - 2, series))
        return series[-1]
    else:
        return series[n-1]

print(fibonacci(10))