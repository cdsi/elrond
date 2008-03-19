from setuptools import setup, find_packages

setup(name='kochanski', version='0.0.1',
      packages=find_packages('src/python'),
      package_dir={'': 'src/python'},
      test_suite='kochanski.test.testsuite')
