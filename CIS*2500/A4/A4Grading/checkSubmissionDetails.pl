#!/usr/bin/perl
use strict;
my @files = `find . | grep -vE "\\.[\\/a-zA-Z0-9_\\-]*\\/\\..*"`;

my $source_files_aip = 1;
my $header_files_aip = 1;
my $readme_aip = 1;
my $has_enough_docs = 1;
my $has_enough_src = 1;
my $has_a_header = 1;
my $readme_is_not_empty = 1;
my $used_list = 0;

my $readme;
my $Makefile;
my $src;
my $include;
my $bin;
my $docs;

my @c_files;
my @h_files;
my @doc_contents;

my %struct_variable_names;

foreach (@files){
	chomp($_);
	if ($_ =~ /.*README(\.txt)?$/){
		$readme = $_;
		print "Found readme: $readme\n";
	}
	if ($_ =~ /.*(M|m)akefile$/){
		$Makefile = $_;
		print "Found makefile: $Makefile\n";
	}
	if ($_ =~ /^\.\/src$/){
		$src = $_;
	}
	if ($_ =~ /^\.\/includes?$/){
		$include = $_;
	}
	if ($_ =~ /^\.\/bin$/){
		$bin = $_;
	}
	if ($_ =~ /^\.\/docs?$/){
		$docs = $_;
	}
	if ($_ =~ /.*\.c$/){
		push(@c_files,$_);
		print "\tFound Source $_\n";
	}
	if($_ =~ /.*\.h$/){
		push(@h_files,$_);
		print "\tFound Header $_\n";
	}
	if ($_ =~ /^\.\/docs?\/.*/){
		push(@doc_contents, $_);
		print "\tFound Doc $_\n";
	}
}

foreach my $file (@c_files){
	if($file !~ /^\.\/src/){
		print "$file is out of place\n";
		$source_files_aip = 0;
	}
	if($file !~ /listTest.c/){
		open(my $myFile, "<$file") or die "Could not open $file";
		print "Computing $file\n";
		while (<$myFile>){
			my $line = $_;
			if ($line =~ /(struct\s+Music|MusicRec)\s*\*?\s+([a-zA-Z0-9_\-\*]*)(\s*|\s*\=\s*[a-zA-Z0-9_\-\*]*)/){
				$struct_variable_names{$2}="$+";
				#print "$2 $+\n"
			}
			foreach my $k (keys %struct_variable_names){
				my $quoted = quotemeta($k);
				if ($line =~ /\s*(\->|\.)\s*next/){
					#print "$line\n";
					$used_list = 1;
				}
			}
		}
		close($myFile);
	}
	else{
		print "Skipping $file\n";
	}
}

print "\n\n\nBEGIN REPORT\n-=-=-=-=-=-=\n";

foreach (@h_files){
	if($_ !~ /^\.\/includes?/){
		print "$_ is out of place\n";
		$header_files_aip = 0;
	}
}

if ($readme !~ /^\.\/README(.txt)?/){
	print "$readme is out of place.\n";
	$readme_aip = 0;
}

if ($#doc_contents < 1){
	print "Not enough doc files.\n";
	$has_enough_docs = 0;
}

if ($#c_files < 1){
	print "Not enough source files.\n";
	$has_enough_src = 0;
}

if ($#h_files < 0){
	print "Not enough header files (should have linkedList.h and one of your own).\n";
	$has_a_header = 0;
}

my @readmestat = stat($readme);
if(10>$readmestat[7]){
	print "Readme not large enough.\n";
	$readme_is_not_empty = 0;
}

if(0==$used_list){
	print "You didn't use the list anywhere.\n";
}

print "Done\n";

open(my $report,">submissionMark.csv");
	print $report "$has_a_header, $has_enough_src, $has_enough_docs, $readme_aip, $header_files_aip, $source_files_aip, $used_list, $readme_is_not_empty\n";
close($report)
