import re
import struct
import sys
from io import TextIOWrapper
from argparse import ArgumentParser, ArgumentDefaultsHelpFormatter
from EncodedFileType import EncodedFileType


class InvertedIndex:

    def __init__(self, inverted_index):
        self.inverted_index = inverted_index

    def __eq__(self, other):
        if isinstance(other, InvertedIndex):
            return other.inverted_index == self.inverted_index
        return False

    def query(self, words: list) -> list:
        assert isinstance(words, list), (
            "query should be provided with a list of words"
        )
        result = []
        for word in words:
            if word in self.inverted_index:
                result.append(self.inverted_index[word])
        return list(set.intersection(*[set(x) for x in result])) if result else []

    def dump(self, filepath: str):
        file = open(filepath, 'wb')
        dict_size = len(self.inverted_index)
        value = struct.pack('>i', dict_size)
        file.write(value)
        for key in self.inverted_index:
            bt_item = key.encode()
            length = len(bt_item)
            value = struct.pack('>i', length)
            file.write(value)
            value = struct.pack('>' + str(length) + 's', bt_item)
            file.write(value)
            key_length = self.inverted_index[key]
            packed_data = struct.pack('>i', len(key_length))
            file.write(packed_data)
            for item in key_length:
                packed_data = struct.pack('>i', int(item))
                file.write(packed_data)
        file.close()

    @classmethod
    def load(cls, filepath: str):
        file = open(filepath, 'rb')
        inverted_index = dict()
        value = file.read(4)
        dict_size = struct.unpack('>i', value)[0]
        for _ in range(dict_size):
            str_length = file.read(4)
            length = struct.unpack('>i', str_length)[0]
            pattern = '>' + str(length) + 's'
            string = file.read(length)
            data = struct.unpack(pattern, string)[0]
            key = str(data.decode())
            inverted_index[key] = []
            read_data = file.read(4)
            count = struct.unpack('>i', read_data)[0]
            for _ in range(count):
                read_data = file.read(4)
                inverted_index[key].append(str(struct.unpack('>i', read_data)[0]))
        file.close()
        return InvertedIndex(inverted_index)


def load_documents(filepath: str):
    """ Extract documents from provided file path

    :rtype: dict
    """
    documents = dict()
    file = open(filepath, 'r', encoding="utf8")
    articles = file.read().split('\n')
    for article in articles:
        article = article.strip()
        if article:
            article_id, article_content = re.split('\t', article.strip(), 1)
            documents[article_id] = article_content
    return documents


def build_inverted_index(documents):
    """ Build and inverted index from provided documents

    :rtype: InvertedIndex
    """
    inverted_index = dict()
    for doc_id in documents:
        terms = documents[doc_id].split()
        for term in terms:
            if term not in inverted_index:
                inverted_index[term] = [doc_id]
            else:
                if doc_id not in inverted_index[term]:
                    inverted_index[term].append(doc_id)
    return InvertedIndex(inverted_index)


def build_inverted_index_and_write_to_file(target_dataset_path, output_file_path):
    documents = load_documents(target_dataset_path)
    inverted_index = build_inverted_index(documents)
    inverted_index.dump(output_file_path)


def callback_build(arguments):
    build_inverted_index_and_write_to_file(arguments.dataset, arguments.output)


def process_queries_from_file(inverted_index_filepath, query_file):
    inverted_index = InvertedIndex.load(inverted_index_filepath)
    for query in query_file:
        print(",".join(inverted_index.query(query.strip().split(" "))))


def process_queries(inverted_index_filepath, query_list):
    inverted_index = InvertedIndex.load(inverted_index_filepath)
    for query in query_list:
        print(",".join(inverted_index.query(query)))


def callback_query(arguments):
    if arguments.query_list:
        process_queries(arguments.inverted_index_filepath, arguments.query_list)
    else:
        process_queries_from_file(arguments.inverted_index_filepath, arguments.query_file)


def setup_parser(parser):
    subparsers = parser.add_subparsers(help="choose command")

    build_parser = subparsers.add_parser(
        "build",
        help="build inverted index and save in binary format into hard drive",
        formatter_class=ArgumentDefaultsHelpFormatter,
    )
    build_parser.set_defaults(callback=callback_build)
    build_parser.add_argument(
        "-d", "--dataset",
        help="path to dataset to load",
    )
    build_parser.add_argument(
        "-o", "--output",
        help="path to store inverted index in a binary format",
    )

    query_parser = subparsers.add_parser(
        "query",
        help="query inverted index",
        formatter_class=ArgumentDefaultsHelpFormatter,
    )
    query_parser.add_argument(
        "-i", "--index",
        dest="inverted_index_filepath",
        help="path to read inverted index in binary form",
    )
    query_parser.add_argument(
        "-q", '--query',
        nargs='+',
        required=False,
        action='append',
        dest='query_list',
        help="query to run against inverted index inverted index",
    )
    query_file_group = query_parser.add_mutually_exclusive_group(required=False)
    query_file_group.add_argument(
        "--query-file-utf8", dest="query_file",
        type=EncodedFileType("r", encoding="utf8"),
        default=TextIOWrapper(sys.stdin.buffer, encoding="utf8"),
        help="query file to get queries for inverted index",
    )
    query_file_group.add_argument(
        "--query-file-cp1251", dest="query_file",
        type=EncodedFileType("r", encoding="cp1251"),
        default=TextIOWrapper(sys.stdin.buffer, encoding="cp1251"),
        help="query file to get queries for inverted index",
    )
    query_parser.set_defaults(callback=callback_query)


def main():
    parser = ArgumentParser(
        prog="inverted-index",
        description="tool to build, dump, load, query inverted index",
        formatter_class=ArgumentDefaultsHelpFormatter,
    )
    setup_parser(parser)
    arguments = parser.parse_args()
    arguments.callback(arguments)


if __name__ == "__main__":
    main()
