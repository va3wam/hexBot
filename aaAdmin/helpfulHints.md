Back to [README](https://github.com/theAgingApprentice/icUnderware/blob/main/README.md)
---

This page contains a list of information that tripped us up while we were creating this repository. May it save you the hours of pain that we went through!

# Table of content

* [Making ASCII banners](#Making-ASCII-banners).
* [Making Markdown internal links](#Making-markdown-lnternal-links).
* [Doxygen ignores main.cpp](#Doxygen-ignores-maincpp). 
* [Doxygen TODO list issue](#Doxygen-TODO-issue).

# Making ASCII banners

We like to put fancy ASCII banners at the top of the header files for all of our classes - because we think its cool. If you want to be like the other cool kids here is what you do:

1. In your browser go to the online text to your ASCII art tool of choice. We prefer [this one](http://www.patorjk.com/software/taag/#p=testall&f=Big&t=aaSocMicro) but have also used [this other one](http://www.patorjk.com/software/taag/#p=display&f=Big&t=aaSocMicro). Any decent tool will do the job. 
2. Select the ```Font``` you like. We have been using ```Colossal```. 
3. Type in the text you want.
4. Click the ```select and copy``` button at the bottom of the page. 

# Making markdown lnternal links

Making a TOC in Markdown files with working links to headings.
The IDs are generated from the content of the header according to the following rules:

1. All non-word text (e.g., punctuation, HTML) is removed. Exception to this is that you must leave one hash ```#``` at the start. 
2. All spaces are converted to hyphens. 
3. Two or more hyphens in a row are converted to one. Same goes for hash characters ```#```.
4. If a header with the same ID has already been generated, a unique incrementing number is appended, starting at 1.

# Doxygen ignores main.cpp

The content of the main.cpp is considered to be global objects which doxygen, by default, does not document. From the doxygen manual:

```
To document a member of a C++ class, you must also document the class itself. The same holds for namespaces. To document a global C function, typedef, enum or preprocessor definition you must first document the file that contains it (usually this will be a header file, because that file contains the information that is exported to other source files).
```
Let's repeat that, because it is often overlooked: to document global objects (functions, typedefs, enum, macros, etc), you must document the file in which they are defined. In other words, there must at least be a ```/** @file */``` line in this file.

# Doxygen TODO issue

When you create a TODO list item use the that you are not going to immediately delete  then follow these rules and they will be nicely formatted in your online documentation:

1. Put them at the bottom of your comment block.
2. Start with an ``@``.
3. Make them all lower case.

For example: 
```
/**
 * @todo This is Doxygen friendly todo ist item.
 */
```
