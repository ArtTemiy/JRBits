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

# with open(f'src/generated/include/{"/".join(namespace)}/{name}.hpp') as header_file, \
#      open(f'src/generated/src/{"/".join(namespace)}/{name}.cpp') as src_file:
#     print(
#         f'''
#         #pragma once
#
#         #include <TopDownEngine/interface/interface.hpp>
#         namespace Game::{namespace} {{
#             ////// {description}
#             class {name} : public Engine::Interface::Interface<{caller_class}> {{
#                 //
#             }};
#         }}
#         '''
#     )