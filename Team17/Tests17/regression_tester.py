import os


def get_source_tests():
    source_test_paths = []
    for subdir_path, subdir_names, files in os.walk('.'):
        if subdir_path.startswith("./ignore"):
            continue
        for file in files:
            if file.endswith('source.txt'):
                source_name = file[:-10]
                source_test_paths.append(source_name)

    return source_test_paths


def get_tests_paths_pairs():
    test_pairs = []
    source_paths = get_source_tests()
    for subdir_path, subdir_names, files in os.walk('.'):
        for file in files:
            if file.endswith('queries.txt'):
                for source_name in source_paths:
                    if file.startswith(source_name):
                        source_file_path = os.path.join(subdir_path, source_name + 'source.txt')
                        query_file_path = os.path.join(subdir_path, file)
                        test_pairs.append((source_file_path, query_file_path))

    return test_pairs


if __name__ == "__main__":
    for pairs in get_tests_paths_pairs():
        print(pairs)
