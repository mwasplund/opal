# Opal
Open Platform Abstraction Layer

## Benchmarks
My old Dell XPS 15 with Win11

|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|               99.39 |       10,061,704.21 |    4.3% |      0.01 | `Concatenate Paths`
|            1,360.93 |          734,790.81 |    1.9% |      0.17 | `Concatenate Paths With Up Reference`
|               12.25 |       81,630,676.41 |    2.3% |      0.01 | `Initialize Path With Root`
|               22.70 |       44,054,327.18 |    1.9% |      0.03 | `Create Windows Path With Root`
|               12.25 |       81,627,610.39 |    2.3% |      0.01 | `Initialize Path Relative`
|            2,483.51 |          402,656.33 |    3.7% |      0.30 | `Get User Profile Directory`
|              652.29 |        1,533,060.45 |    4.5% |      0.08 | `Get Current Directory`
|               10.78 |       92,772,984.51 |    2.5% |      0.01 | `SemanticVersion ToString Major Only`
|               24.67 |       40,529,523.51 |    2.6% |      0.03 | `SemanticVersion ToString With Minor`
|               38.48 |       25,984,810.93 |    3.5% |      0.05 | `SemanticVersion ToString With Minor and Path`
|               14.03 |       71,251,652.40 |    2.3% |      0.02 | `SemanticVersion Parse Major Only`
|               26.83 |       37,268,496.07 |    2.2% |      0.03 | `SemanticVersion Parse With Minor`
|               38.17 |       26,197,729.46 |    3.9% |      0.05 | `SemanticVersion Parse With Minor and Path`


Ubuntu 24.04 Lenovo Yoga slim 7i performance mode
|               ns/op |                op/s |    err% |     total | benchmark
|--------------------:|--------------------:|--------:|----------:|:----------
|              125.81 |        7,948,462.08 |    2.1% |      0.02 | `Concatenate Paths`
|              989.88 |        1,010,226.95 |    2.2% |      0.12 | `Concatenate Paths With Up Reference`
|               32.85 |       30,438,420.97 |    2.0% |      0.04 | `Initialize Path With Root`
|              130.75 |        7,648,116.88 |    0.3% |      0.16 | `Create Windows Path With Root`
|               37.77 |       26,475,138.91 |    1.4% |      0.05 | `Initialize Path Relative`
|               78.10 |       12,803,682.27 |    2.4% |      0.01 | `Get User Profile Directory`
|            1,019.28 |          981,086.95 |    2.3% |      0.12 | `Get Current Directory`
|               19.62 |       50,974,609.28 |    2.4% |      0.02 | `SemanticVersion ToString Major Only`
|               71.13 |       14,058,698.61 |    1.7% |      0.09 | `SemanticVersion ToString With Minor`
|              125.48 |        7,969,336.94 |    0.4% |      0.15 | `SemanticVersion ToString With Minor and Path`
|               28.70 |       34,838,378.06 |    3.1% |      0.03 | `SemanticVersion Parse Major Only`
|               52.03 |       19,220,036.79 |    1.8% |      0.06 | `SemanticVersion Parse With Minor`
|               64.56 |       15,488,636.56 |    0.3% |      0.08 | `SemanticVersion Parse With Minor and Path`