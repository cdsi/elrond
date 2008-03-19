from setuptools import setup, find_packages

setup(packages=find_packages('src/python'),
      package_dir={'': 'src/python'},
      test_suite='kochanski.test.testsuite')
