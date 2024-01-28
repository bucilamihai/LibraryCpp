#pragma once


class Tests
{
public:
	void FilterByTitle_EmptyList() const;
	void FilterByTitle_EmptyFilteredList() const;
	void FilterByTitle_NormalFilteredList() const;

	void runDomainGettersTest() const;
	void runDomainSettersTest() const;

	void runRepoAddTest() const;
	void runRepoDeleteTest() const;
	void runRepoModifyTest() const;
	void runRepoFindTest() const;
	void runRepoDeleteAllTest() const;

	void runServiceAddTest() const;
	void runServiceDeleteTest() const;
	void runServiceModifyTest() const;
	void runServiceFindTest() const;
	void runServiceFilterByTitleTest() const;
	void runServiceFilterByYearTest() const;
	void runServiceSortByTitle() const;
	void runServiceSortByAuthor() const;
	void runServiceSortByYearAndGenre() const;

	void runTitleValidator() const;
	void runAuthorValidator() const;
	void runGenreValidator() const;
	void runYearValidator() const;
	void runBookValidator() const;

	void runRepoRentalAddTest() const;
	void runServiceRentalAddTest() const;
	void runRepoRentalDeleteTest() const;
	void runServiceRentalDeleteTest() const;
	void runServiceRentalGenerateTest() const;
	void runServiceRentalExportTest() const;

	void runFakeRepoTest() const;
	void runDomainTest() const;
	void runRepoTest() const;
	void runServiceTest() const;
	void runValidatorTest() const;
	void runRentalTest() const;
	void runUndoTest() const;
	void runAllTests() const;
};