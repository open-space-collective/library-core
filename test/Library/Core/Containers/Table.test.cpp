////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Table.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Table.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Containers_Table, Constructor)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        EXPECT_NO_THROW(Table table(header, rows) ;) ;

    }

    {

        const Array<String> header = { "Column A", "Column B" } ;
        
        EXPECT_NO_THROW(Table table(header) ;) ;

    }

    {

        const Array<String> header = { "Column A" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        EXPECT_ANY_THROW(Table table(header, rows) ;) ;

    }

}

TEST (Library_Core_Containers_Table, CopyConstructor)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        const Table copyTable(table) ;

        EXPECT_NE(&table, &copyTable) ;
        EXPECT_EQ(table, copyTable) ;

    }

}

TEST (Library_Core_Containers_Table, CopyAssignmentOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        const Table copyTable = table ;

        EXPECT_NE(&table, &copyTable) ;
        EXPECT_EQ(table, copyTable) ;

    }

}

TEST (Library_Core_Containers_Table, EqualToOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_TRUE(table == table) ;

    }

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header, rows } ;
        const Table table_B = { header, rows } ;

        EXPECT_TRUE(table_A == table_B) ;

    }

    {

        const Array<String> header_A = { "Column A", "Column B" } ;
        const Array<Row> rows_A =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header_A, rows_A } ;

        const Array<String> header_B = { "Column A", "Column B" } ;
        const Array<Row> rows_B =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() }
        } ;

        const Table table_B = { header_B, rows_B } ;

        EXPECT_FALSE(table_A == table_B) ;

    }

    {

        const Array<String> header_A = { "Column A", "Column B" } ;
        const Array<Row> rows_A =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header_A, rows_A } ;

        const Array<String> header_B = { "Column A", "Column B", "Column C" } ;
        const Array<Row> rows_B =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_B = { header_B, rows_B } ;

        EXPECT_FALSE(table_A == table_B) ;

    }

}

TEST (Library_Core_Containers_Table, NotEqualToOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_FALSE(table != table) ;

    }

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header, rows } ;
        const Table table_B = { header, rows } ;

        EXPECT_FALSE(table_A != table_B) ;

    }

    {

        const Array<String> header_A = { "Column A", "Column B" } ;
        const Array<Row> rows_A =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header_A, rows_A } ;

        const Array<String> header_B = { "Column A", "Column B" } ;
        const Array<Row> rows_B =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() }
        } ;

        const Table table_B = { header_B, rows_B } ;

        EXPECT_TRUE(table_A != table_B) ;

    }

    {

        const Array<String> header_A = { "Column A", "Column B" } ;
        const Array<Row> rows_A =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_A = { header_A, rows_A } ;

        const Array<String> header_B = { "Column A", "Column B", "Column C" } ;
        const Array<Row> rows_B =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table_B = { header_B, rows_B } ;

        EXPECT_TRUE(table_A != table_B) ;

    }

}

TEST (Library_Core_Containers_Table, SubscriptOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_NO_THROW(table[0]) ;

        const Row& firstRow = table[0] ;

        EXPECT_EQ(Object::Integer(123), firstRow[0]) ;
        EXPECT_EQ(Object::Real(123.456), firstRow[1]) ;
        EXPECT_ANY_THROW(firstRow[2]) ;

        EXPECT_NO_THROW(table[1]) ;

        const Row& secondRow = table[1] ;

        EXPECT_EQ(Object::String("Hello"), secondRow[0]) ;
        EXPECT_FALSE(secondRow[1].isDefined()) ;
        EXPECT_ANY_THROW(secondRow[2]) ;

        const Row& thirdRow = table[2] ;

        EXPECT_EQ(Object::String("World!"), thirdRow[0]) ;
        EXPECT_ANY_THROW(thirdRow[1]) ;

        EXPECT_ANY_THROW(table[3]) ;

    }

}

TEST (Library_Core_Containers_Table, FunctionCallOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_EQ(Object::Integer(123), table(0, 0)) ;
        EXPECT_EQ(Object::Real(123.456), table(0, 1)) ;
        EXPECT_ANY_THROW(table(0, 2)) ;

        EXPECT_EQ(Object::String("Hello"), table(1, 0)) ;
        EXPECT_FALSE(table(1, 1).isDefined()) ;
        EXPECT_ANY_THROW(table(1, 2)) ;

        EXPECT_EQ(Object::String("World!"), table(2, 0)) ;
        EXPECT_ANY_THROW(table(2, 1)) ;

        EXPECT_ANY_THROW(table(3, 0)) ;

    }

}

TEST (Library_Core_Containers_Table, StreamOperator)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << table << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Core_Containers_Table, Iterator)
{

    using library::core::types::Index ;
    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        Index index = 0 ;

        for (const auto& row : table)
        {

            if (index == 0)
            {

                EXPECT_EQ(Object::Integer(123), row[0]) ;
                EXPECT_EQ(Object::Real(123.456), row[1]) ;

            }
            else if (index == 1)
            {

                EXPECT_EQ(Object::String("Hello"), row[0]) ;
                EXPECT_FALSE(row[1].isDefined()) ;
                
            }
            else if (index == 2)
            {

                EXPECT_EQ(Object::String("World!"), row[0]) ;
                
            }
            else
            {
                FAIL() ;
            }

            index++ ;

        }

        EXPECT_EQ(3, index) ;

    }

}

TEST (Library_Core_Containers_Table, IsEmpty)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_FALSE(table.isEmpty()) ;

    }

    {

        const Array<String> header = { "Column A", "Column B" } ;
        
        const Table table = { header } ;

        EXPECT_TRUE(table.isEmpty()) ;

    }

    {

        EXPECT_TRUE(Table::Empty().isEmpty()) ;

    }

}

TEST (Library_Core_Containers_Table, GetRowCount)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_EQ(3, table.getRowCount()) ;

    }

    {

        EXPECT_EQ(0, Table::Empty().getRowCount()) ;

    }

}

TEST (Library_Core_Containers_Table, GetColumnCount)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        const Table table = { header, rows } ;

        EXPECT_EQ(2, table.getColumnCount()) ;

    }

    {

        EXPECT_EQ(0, Table::Empty().getColumnCount()) ;

    }

}

TEST (Library_Core_Containers_Table, AddRow)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        
        Table table = { header } ;

        EXPECT_TRUE(table.isEmpty()) ;
        EXPECT_EQ(2, table.getColumnCount()) ;

        table.addRow({ Object::Integer(123), Object::Real(123.456) }) ;
        table.addRow({ Object::String("Hello"), Object::Undefined() }) ;
        table.addRow({ Object::String("World!") }) ;

        EXPECT_FALSE(table.isEmpty()) ;
        EXPECT_EQ(2, table.getColumnCount()) ;

    }

    {

        const Array<String> header = { "Column A" } ;
        
        Table table = { header } ;

        EXPECT_TRUE(table.isEmpty()) ;
        EXPECT_EQ(1, table.getColumnCount()) ;

        EXPECT_NO_THROW(table.addRow({ Object::Integer(123), Object::Real(123.456) })) ;

        EXPECT_EQ(2, table.getColumnCount()) ;

    }

}

TEST (Library_Core_Containers_Table, Clear)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;

    {

        const Array<String> header = { "Column A", "Column B" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Real(123.456) },
            { Object::String("Hello"), Object::Undefined() },
            { Object::String("World!") }
        } ;

        Table table = { header, rows } ;

        EXPECT_FALSE(table.isEmpty()) ;
        
        table.clear() ;

        EXPECT_TRUE(table.isEmpty()) ;

    }

}

TEST (Library_Core_Containers_Table, Empty)
{

    using library::core::ctnr::Table ;

    {

        EXPECT_NO_THROW(Table::Empty()) ;
        EXPECT_TRUE(Table::Empty().isEmpty()) ;

    }

}

TEST (Library_Core_Containers_Table, Load)
{

    using library::core::types::String ;
    using library::core::ctnr::Array ;
    using library::core::ctnr::Object ;
    using library::core::ctnr::Table ;
    using library::core::ctnr::table::Row ;
    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const Array<String> header = { "A", "B", "C", "D", "E", "F" } ;
        const Array<Row> rows =
        {
            { Object::Integer(123), Object::Integer(-123), Object::Integer(123), Object::Real(123.456), Object::Real(-123.456), Object::Real(123.456) },
            { Object::String("Hello"), Object::String("World"), Object::String("!"), Object::String("Hello,"), Object::String("Wo\"\"rld") },
            { Object::Integer(1), Object::Undefined(), Object::Integer(3), Object::Undefined(), Object::Integer(5) }
        } ;

        const Table referenceTable = { header, rows } ;

        const File file = File::Path(Path::Parse("../test/Library/Core/Containers/Table/A.csv")) ;

        const Table table = Table::Load(file) ;

        EXPECT_EQ(referenceTable, table) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////