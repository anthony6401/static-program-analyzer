import os
import sys
import xml.etree.ElementTree as ET
import subprocess


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


def get_results():
    tree = ET.parse("../Code17/tests/out.xml")
    queries = tree.getroot()[1]
    queries_count = 0
    correct_id = []
    wrong_id = []
    timeout_id = []
    for query in queries:
        queries_count += 1
        query_id = query[0].text
        tag_type = query[2].tag

        if tag_type == "timeout":
            timeout_id.append(query_id)
            continue
        if tag_type == "exception":
            wrong_id.append(query_id)
            continue

        is_result_tag = query[5].tag
        if is_result_tag == "failed":
            wrong_id.append(query_id)
            continue
        correct_id.append(query_id)

    return queries_count, correct_id, wrong_id, timeout_id


def run_autotester(autotester_path, test_path_pairs):
    total_count = 0
    total_correct_count = 0
    total_wrong_count = 0
    total_timeout_count = 0
    run_count = 0
    for source_path, query_path in test_path_pairs:
        run_count += 1
        subprocess.run([autotester_path, source_path, query_path, "../Code17/tests/out.xml"], stdout=subprocess.DEVNULL)
        print("---------- AUTOTESTER RUNNING COMPLETED ------------")
        try:
            queries_count, correct_id, wrong_id, timeout_id = get_results()
        except ET.ParseError:
            raise RuntimeError("Unable to parse out.xml")

        total_count += queries_count
        total_correct_count += len(correct_id)
        total_wrong_count += len(wrong_id)
        total_timeout_count += len(timeout_id)

        print(f"[{query_path}] {len(correct_id)}/{queries_count} passing test cases for run {run_count}.")

        if len(wrong_id) > 0:
            print(f"\tWrong cases: {wrong_id}")
        if len(timeout_id) > 0:
            print(f"\tTimeout cases: {timeout_id}")

    return total_count, total_correct_count, total_wrong_count, total_timeout_count


if __name__ == "__main__":
    try:
        test_path_pairs = get_tests_paths_pairs()
        total_count, total_correct_count, total_wrong_count, total_timeout_count = run_autotester(sys.argv[1], test_path_pairs)

        print(f"Correct test cases: {total_correct_count}/{total_count}.")
        print(f"Wrong test cases: {total_wrong_count + total_timeout_count}/{total_count}.")
    except Exception as e:
        print(e)




