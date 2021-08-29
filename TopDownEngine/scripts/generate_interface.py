import os
import sys

import yaml

path_to_yaml = sys.argv[1]
print(f'Generating for file: {path_to_yaml}')

yaml_file = yaml.safe_load(open(path_to_yaml))

namespace = yaml_file['name'].split('::')
name = yaml_file['name']
description = yaml_file["description"]
caller_class = yaml_file["caller-class"]

print(yaml_file)
