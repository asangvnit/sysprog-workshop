<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Your assignments](#your-assignments)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Your assignments

You can form groups of 2-3 and split the work amongst yourself. Tell me the name of your project and I will create a project for you on my gerrit server. Instead, you can also choose to publish your work on [github](https://github.com/). If you decide to use github, you MUST use the [pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request) based workflow to integrate your changes.

Create a program that implements a doubly linked list in C++. The entire assignment should be build using `cmake` based build and test systems. Expectations are as follows:

- You should publish the API in a separate header file.
- The results should be published in a separate header file.
- Your implementation should be tested using [GoogleTest](https://github.com/google/googletest/tree/main). This [Sample](https://github.com/google/googletest/blob/b2b9072ecbe874f5937054653ef8f2731eb0f010/googletest/samples/sample5_unittest.cc) shows how to go about it.
- The unit test should be integrated with the build system using `cmake`.
- The development process should go through the code reviews and integration process explained earlier.

Final results should be published on gerrit-server. Bonus points for those who can integrate their build system with [github actions](https://docs.github.com/en/actions).
