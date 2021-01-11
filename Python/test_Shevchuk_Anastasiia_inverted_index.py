import pytest
from task_Shevchuk_Anastasiia_inverted_index import load_documents, build_inverted_index, process_queries, \
    InvertedIndex, build_inverted_index_and_write_to_file

DATASET_BIG_PATH = "wikipedia_sample"
DATASET_TINY_STR = """
        123	some word A_word and nothing
        2	some word B_word in this dataset
        5	famous_phrases to be or not to be
        37	all words such as A_word and B_word are here
    """
QUERIES_SAMPLE = """
    A_word
    B_word
    A_word B_word 
    """


@pytest.mark.skip
def test_can_load_wikipedia_sample():
    documents = load_documents(DATASET_BIG_PATH)
    assert len(documents) == 4100, (
        "Wikipedia sample has been loaded incorrectly"
    )


@pytest.fixture()
def wikipedia_documents():
    documents = load_documents(DATASET_BIG_PATH)
    return documents


@pytest.fixture
def wikipedia_inverted_index(wikipedia_documents):
    wikipedia_inverted_index = build_inverted_index(wikipedia_documents)
    return wikipedia_inverted_index


@pytest.mark.skip
def test_can_build_and_query_inverted_index(wikipedia_inverted_index):
    doc_ids = wikipedia_inverted_index.query(["wikipedia"])
    assert isinstance(doc_ids, list), "inverted index query should return a list"


@pytest.fixture()
def tiny_dataset_fio(tmpdir):
    dataset_fio = tmpdir.join("dataset.txt")
    dataset_fio.write(DATASET_TINY_STR)
    return dataset_fio


def test_can_load_small_wikipedia_sample(tiny_dataset_fio):
    documents = load_documents(tiny_dataset_fio)
    assert len(documents) == 4, (
        "Wikipedia sample has been loaded incorrectly"
    )


def test_can_load_documents(tiny_dataset_fio):
    documents = load_documents(tiny_dataset_fio)
    reference_documents = {
        "123": "some word A_word and nothing",
        "2": "some word B_word in this dataset",
        "5": "famous_phrases to be or not to be",
        "37": "all words such as A_word and B_word are here",
    }
    assert reference_documents == documents, (
        "load_documents incorrectly loaded dataset"
    )


@pytest.fixture()
def small_sample_wikipedia_documents(tiny_dataset_fio):
    documents = load_documents(tiny_dataset_fio)
    return documents


@pytest.fixture
def small_wikipedia_inverted_index(small_sample_wikipedia_documents):
    small_wikipedia_inverted_index = build_inverted_index(small_sample_wikipedia_documents)
    return small_wikipedia_inverted_index


def test_can_build_and_query_inverted_index(small_wikipedia_inverted_index):
    doc_ids = small_wikipedia_inverted_index.query(["A_word"])
    assert isinstance(doc_ids, list), "inverted index query should return a list"


@pytest.mark.parametrize(
    "query, reference_answer",
    [
        pytest.param(["A_word"], ["123", "37"], id="A_word"),
        pytest.param(["B_word"], ["2", "37"], id="B_word"),
        pytest.param(["A_word", "B_word"], ["37"], id="both words"),
        pytest.param(["word_does_not_exist"], [], id="word does not exist"),
    ],
)
def test_query_inverted_index_intersect_results(tiny_dataset_fio, query, reference_answer):
    documents = load_documents(tiny_dataset_fio)
    tiny_inverted_index = build_inverted_index(documents)
    answer = tiny_inverted_index.query(query)
    assert sorted(answer) == sorted(reference_answer), (
        f"Expected answer is {reference_answer}, but {answer} got"
    )


def test_can_dump_and_load_small_inverted_index(tmpdir, small_wikipedia_inverted_index):
    index_fio = tmpdir.join("dump.bin")
    small_wikipedia_inverted_index.dump(index_fio)
    loaded_inverted_index = InvertedIndex.load(index_fio)
    assert small_wikipedia_inverted_index.__eq__(loaded_inverted_index), (
        "load should return the same inverted index"
    )


@pytest.fixture
def small_wikipedia_inverted_index_store_path(tmpdir, small_wikipedia_inverted_index):
    small_wikipedia_inverted_index_store_path = tmpdir.join("dump_inverted_index.bin")
    small_wikipedia_inverted_index.dump(small_wikipedia_inverted_index_store_path)
    return small_wikipedia_inverted_index_store_path


@pytest.fixture()
def queries_ut8_file_sample(tmpdir):
    queries_file_sample = tmpdir.join("queries.txt")
    queries_file_sample.write(QUERIES_SAMPLE.encode("utf8"))
    return queries_file_sample


@pytest.fixture()
def queries_cp1251_file_sample(tmpdir):
    queries_file_sample = tmpdir.join("queries.txt")
    queries_file_sample.write(QUERIES_SAMPLE.encode("cp1251"))
    return queries_file_sample


def test_process_query_process_can_process_queries_from_utf8_file(capsys, queries_ut8_file_sample,
                                                                  small_wikipedia_inverted_index_store_path):
    expected_result = [['123', '37'], ['37', '2'], ['37']]
    with open(queries_ut8_file_sample) as queries_fin:
        process_queries(
            inverted_index_filepath=small_wikipedia_inverted_index_store_path,
            query_file=queries_fin,
        )
        captured = capsys.readouterr()
    result = [str.split(',') for str in captured.out.strip().split('\n')]
    assert len(expected_result) == len(result)
    for a, b in zip(expected_result, result):
        assert sorted(a) == sorted(b)


def test_can_build_inverted_index_from_documents_and_write_to_file(tmpdir, tiny_dataset_fio,
                                                                   small_wikipedia_inverted_index):
    output_path = tmpdir.join("loaded_inverted_index.bin")
    build_inverted_index_and_write_to_file(
        target_dataset_path=tiny_dataset_fio,
        output_file_path=output_path
    )
    loaded_inverted_index = InvertedIndex.load(output_path)
    assert small_wikipedia_inverted_index.__eq__(loaded_inverted_index), (
        "load should return the same inverted index"
    )
