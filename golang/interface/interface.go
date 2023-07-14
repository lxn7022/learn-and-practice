package interface0

import (
	"io"
	"os"
)

//这个例子展示了类型断言用于选择可能的行为，这儿如果一个io.Writer支持WriteString则可以直接使用，从而避免分配临时内存

func writeString(w io.Writer, s string) (n int, err error) {
	type stringWriter interface {
		WriteString(string) (n int, err error)
	}
	if sw, ok := w.(stringWriter); ok {
		//fmt.Print("<use WriteString>")
		return sw.WriteString(s) // avoid temporary copy
	}
	return w.Write([]byte(s)) // allocate temporary copy
}

func writeHeader(w io.Writer, contentType string) error {
	if _, err := writeString(w, "Content-Type: "); err != nil {
		return err
	}
	if _, err := io.WriteString(w, contentType); err != nil { //系统自带的io.WriteString实现和上面一样
		return err
	}
	return nil
}

func main() {
	writeHeader(os.Stdout, "test")
}
