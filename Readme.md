# Kpool

## Overview

Kpool is a command-line utility which is part of a more general pipeline to identify sex-specific Kmers in pooled-sequencing data. Kpool implements two functions:
- merging kmer tables from each pool into a common table (kmer tables are obtained with Jellyfish)
- filtering this table for min/max frequencies in homogametic and heterogametic sex

Kpool was developed as part of a project by the [LPGP](https://www6.rennes.inra.fr/lpgp/) lab from INRA, Rennes, France. It is still in beta and not officially released.

A more detailed README will be available soon.

## Installation

```
# Clone the repository
git clone https://github.com/INRA-LPGP/kpool.git
# Navigate to the kpool directory
cd kpool
# Build kpool
make
```

## Basic usage

Currently, Kpool has two commands:

- `merge`: merge kmer tables from each pool into a common table (kmer tables are obtained with Jellyfish)
- `filter`: filter a merged table based on kmer min/max frequencies in homogametic and heterogametic sex

### Merge

```
kpool merge -m male_table -f female_table -o output_file
```

#### Options:

Flag | Type       | Description                                              | Default |
-----|------------|----------------------------------------------------------|---------|
-m   |  `string`  |  Path to the male kmers table (output from Jellyfish)    |         |
-f   |  `string`  |  Path to the female kmers table (output from Jellyfish)  |         |
-o   |  `string`  |  Path to the output file (merged kmers table)            |         |


### Filter

```
kpool filter -i merged_table -o output_file -s heterogametic_sex --min-het min_hetero_cov [ --max-het max_hetero_cov --max-hom max_homo_cov ]
```

#### Options:

Flag       | Type       | Description                                              | Default |
-----------|------------|----------------------------------------------------------|---------|
-i         |  `string`  |  Path to a merged kmers table                            |         |
-o         |  `string`  |  Path to the ouput file (filter kmers table)             |         |
-s         |  `string`  |  Hetergogametic sex (M / F)                              |         |
--min-het  |  `int`     |  Minimum kmer coverage in the heterogametic sex          |         |
--max-het  |  `int`     |  Maximum kmer coverage in the heterogametic sex          | 1000000 |
--max-hom  |  `int`     |  Maximum kmer coverage in the homogametic sex            |       0 |
