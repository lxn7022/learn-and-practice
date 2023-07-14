package container

import "testing"

func TestExamRing(t *testing.T) {
	tests := []struct {
		name string
	}{
		// TODO: Add test cases.
		{"TestExamRing"},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			ExamRing()
		})
	}
}
