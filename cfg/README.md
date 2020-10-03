# Configuration files

---
## Service config
---

**[main]**<br/>

| Parameter | Description                                 | Type | Default | Range |
| :-------- | :------------------------------------------ | :--: | :-----: | :---: |
| debug     | Flag if need trace service info to log file | bool | *false* |   -   |

<br/>

---

**[receive]**<br/>

| Parameter | Description                                | Type   | Default | Range |
| :-------- | :----------------------------------------- | :----  | :-----: | :---: |
| target    | Inter Process Communications               | string | *ipc*   |   -   |
| prefix    | ZCM in channel prefix                      | string |         |   -   |
| channel   | ZCM out channel prefix                     | string |         |   -   |

<br/>

---

**[send]**<br/>

| Parameter | Description                                | Type   | Default | Range |
| :-------- | :----------------------------------------- | :----  | :-----: | :---: |
| target    | Inter Process Communications               | string | *ipc*   |   -   |
| prefix    | ZCM in channel prefix                      | string |         |   -   |
| channel   | ZCM out channel prefix                     | string |         |   -   |

<br/>

---

**[logs]**<br/>

| Parameter    | Description                                              | Type   | Default           | Range    |
| :----------- | :------------------------------------------------------- | :----  | :---------------: | :---:    |
| need_trace   | Flag if need log service messages to file                | bool   | true              |   -      |
| need_shared  | Flag if need write all logging levels to one file        | bool   | true              |   -      |
| shared_name  | Shared log filename                                      | string | *$$FULL_APP.log*  |   -      |
| need_leveled | Flag if need write each level of logging to its own file | bool   | true              |   -      |
| leveled_path | Leveled logs path                                        | string | *$$APP_PATH/logs* |   -      |
| file_sizes   | Log max size in Kb                                       | uint   | 1e6               | 0 - 2^32 |
| rotates      | Max logs count                                           | uint   | 3                 | 0 - 2^16 |

<br/>

---
## Clang-Tidy static analyzer config
---

See [full list of CLang-Tidy checks](https://clang.llvm.org/extra/clang-tidy/checks/list.html).

```
google-build-explicit-make-pair
google-build-namespaces
google-upgrade-googletest-case
google-runtime-int
google-readability-todo
google-readability-casting
google-readability-avoid-underscore-in-googletest-name
google-global-names-in-headers

fuchsia-multiple-inheritance
fuchsia-statically-constructed-objects

hicpp-avoid-goto

linuxkernel-must-use-errs

clang-analyzer-core.uninitialized.CapturedBlockVariable
clang-analyzer-cplusplus.InnerPointer
clang-analyzer-nullability.NullableReturnedFromNonnull
clang-analyzer-optin.portability.UnixAPI
clang-analyzer-valist.CopyToSelf
clang-analyzer-valist.Uninitialized
clang-analyzer-valist.Unterminated

bugprone-argument-comment
bugprone-assert-side-effect
bugprone-bad-signal-to-kill-thread
bugprone-bool-pointer-implicit-conversion
bugprone-branch-clone
bugprone-dangling-handle
bugprone-dynamic-static-initializers
bugprone-fold-init-type
bugprone-inaccurate-erase
bugprone-incorrect-roundings
bugprone-infinite-loop
bugprone-integer-division
bugprone-macro-parentheses
bugprone-macro-repeated-side-effects
bugprone-misplaced-operator-in-strlen-in-alloc
bugprone-misplaced-pointer-arithmetic-in-alloc
bugprone-misplaced-widening-cast
bugprone-move-forwarding-reference
bugprone-multiple-statement-macro
bugprone-no-escape
bugprone-not-null-terminated-result
bugprone-parent-virtual-call
bugprone-posix-return
bugprone-reserved-identifier
bugprone-signed-char-misuse
bugprone-sizeof-container
bugprone-sizeof-expression
bugprone-spuriously-wake-up-functions
bugprone-string-constructor
bugprone-string-integer-assignment
bugprone-suspicious-include
bugprone-suspicious-memset-usage
bugprone-suspicious-missing-comma
bugprone-suspicious-semicolon
bugprone-suspicious-string-compare
bugprone-swapped-arguments
bugprone-throw-keyword-missing
bugprone-too-small-loop-variable
bugprone-undefined-memory-manipulation
bugprone-undelegated-constructor
bugprone-unhandled-self-assignment
bugprone-unused-raii
bugprone-unused-return-value
bugprone-use-after-move

llvm-include-order
llvm-namespace-comment
llvm-prefer-isa-or-dyn-cast-in-conditionals
llvm-twine-local
llvmlibc-callee-namespace
llvmlibc-implementation-in-namespace

readability-use-anyofallof
readability-uppercase-literal-suffix
readability-uniqueptr-delete-release
readability-string-compare
readability-static-definition-in-anonymous-namespace
readability-simplify-subscript-expr
readability-simplify-boolean-expr
readability-redundant-string-init
readability-redundant-string-cstr
readability-redundant-smartptr-get
readability-redundant-preprocessor
readability-redundant-function-ptr-dereference
readability-redundant-declaration
readability-redundant-control-flow
readability-redundant-access-specifiers
readability-qualified-auto
readability-magic-numbers
readability-named-parameter
readability-non-const-parameter
readability-redundant-member-init
readability-container-size-empty
readability-deleted-default
readability-function-size
readability-implicit-bool-conversion
readability-inconsistent-declaration-parameter-name
readability-isolate-declaration

mpi-buffer-deref
mpi-type-mismatch

openmp-exception-escape
openmp-use-default-none

performance-inefficient-vector-operation
performance-inefficient-string-concatenation
performance-inefficient-algorithm
performance-implicit-conversion-in-loop
performance-for-range-copy
performance-faster-string-find

misc-new-delete-overloads
misc-redundant-expression
misc-static-assert
misc-throw-by-value-catch-by-reference
misc-unconventional-assign-operator
misc-uniqueptr-reset-release
misc-unused-alias-decls
misc-unused-using-decls
misc-unused-parameters

modernize-use-using
modernize-use-uncaught-exceptions
modernize-use-transparent-functors
modernize-use-override
modernize-use-nullptr
modernize-use-equals-default
modernize-use-emplace
modernize-use-default-member-init
modernize-use-bool-literals
modernize-use-auto
modernize-unary-static-assert
modernize-shrink-to-fit
modernize-return-braced-init-list
modernize-replace-disallow-copy-and-assign-macro
modernize-replace-auto-ptr
modernize-redundant-void-arg
modernize-raw-string-literal
modernize-pass-by-value
modernize-make-unique
modernize-make-shared
modernize-deprecated-ios-base-aliases
modernize-deprecated-headers
modernize-concat-nested-namespaces
modernize-avoid-c-arrays
modernize-avoid-bind

cert-dcl21-cpp
cert-dcl50-cpp
cert-dcl58-cpp
cert-mem57-cpp
cert-msc50-cpp
cert-oop57-cpp

cppcoreguidelines-avoid-goto
cppcoreguidelines-avoid-non-const-global-variables
cppcoreguidelines-init-variables
cppcoreguidelines-macro-usage
cppcoreguidelines-narrowing-conversions
cppcoreguidelines-no-malloc
cppcoreguidelines-owning-memory
cppcoreguidelines-pro-bounds-constant-array-index
cppcoreguidelines-pro-type-member-init
cppcoreguidelines-pro-type-union-access
cppcoreguidelines-slicing
```

---