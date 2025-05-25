#!/bin/bash
# make_files.sh

declare -A files

files[Creational]="factory.cpp abstract.cpp singleton.cpp prototype.cpp builder.cpp"
files[Structural]="adapter.cpp bridge.cpp composite.cpp decorator.cpp facade.cpp flyweight.cpp proxy.cpp"
files[Behavioral]="chain_of_responsibilty.cpp command.cpp interpreter.cpp mediator.cpp memento.cpp observer.cpp state.cpp strategy.cpp template.cpp visitor.cpp"
files[ECS]="ecs_example.cpp"

for category in "${!files[@]}"; do
    mkdir -p "$category" # make dir if dne
    for filename in ${files[$category]}; do
        filepath="${category}/${filename}"
        if [ ! -f "$filepath" ]; then
            echo "// ${filename}" > "$filepath"
            echo "created $filepath"
        else
            echo "$filepath already exists. skipping"
        fi
    done
done

