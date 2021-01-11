from argparse import FileType, ArgumentTypeError


class EncodedFileType(FileType):
    def __cal__(self, string):
        if string == '-':
            if 'r' in self._mode:
                stdin = TextIOWrapper(sys.stdin.buffer, encoding=self._encoding)
                return stdin
            if 'w' in self._mode:
                stdout = TextIOWrapper(sys.stdout.buffer, encoding=self._encoding)
                return stdout
            msg = 'argument "-" with mode %r' % self._mode
            raise ValueError(msg)

        # all other arguments are used as file names
        try:
            return open(string, self._mode, self._bufsize, self._encoding,
                        self._errors)
        except OSError as error:
            args = {'filename': string, 'error': error}
            message = "can't open '%(filename)s': %(error)s"
            raise ArgumentTypeError(message % args)
