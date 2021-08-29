from jinja2 import Template

actors = list(map(
    lambda x: x.strip(),
    open('configs/actors_list.gcfg', 'r').readlines()
))
with open('Game/src/_gen/actors_creator_helper.hpp', 'w+') as output_file:
    print(
        Template(open('TopDownEngine/scripts/templates/actor_creator_helper_list.cpp.jinja', 'r').read()) \
        .render(actors=actors),
        file=output_file
    )
